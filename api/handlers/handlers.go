package handlers

import (
	"encoding/json"
	"net/http"
	"strconv"
	"time"

	"api/models"
	"api/storage"
	"html/template"
	"log"
)

func PostPositionHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
		return
	}

	var pos models.Position
	if err := json.NewDecoder(r.Body).Decode(&pos); err != nil {
		http.Error(w, "Invalid request body", http.StatusBadRequest)
		return
	}

	pos.Timestamp = time.Now()
	if err := storage.SavePosition(pos); err != nil {
		log.Printf("Error saving position: %v", err)
		http.Error(w, "Database error", http.StatusInternalServerError)
		return
	}

	w.WriteHeader(http.StatusCreated)
}

func GetPositionsHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodGet {
		http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
		return
	}

	positions, err := storage.GetPositions()
	if err != nil {
		http.Error(w, "Database error", http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(positions)
}

func MapHandler(w http.ResponseWriter, r *http.Request) {
	positions, err := storage.GetPositions()
	if err != nil {
		log.Printf("Error getting positions: %v", err)
		http.Error(w, "Database error", http.StatusInternalServerError)
		return
	}

	positionsJSON, err := json.Marshal(positions)
	if err != nil {
		http.Error(w, "JSON encoding error", http.StatusInternalServerError)
		return
	}

	tmpl := `<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Carte des Positions</title>
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.7.1/dist/leaflet.css" />
    <script src="https://unpkg.com/leaflet@1.7.1/dist/leaflet.js"></script>
    <style>
        :root {
            --primary-color: #2c3e50;
            --secondary-color: #34495e;
            --accent-color: #f39c12;
            --text-color: #ecf0f1;
        }
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: 'Arial', sans-serif;
        }
        body {
            display: flex;
            height: 100vh;
            background: var(--primary-color);
            color: var(--text-color);
        }
        #sidebar {
            width: 320px;
            background: var(--secondary-color);
            padding: 20px;
            overflow-y: auto;
            display: flex;
            flex-direction: column;
            gap: 15px;
        }
        h2 {
            text-align: center;
            color: var(--accent-color);
            font-size: 1.8rem;
        }
        #map-container {
            flex: 1;
            display: flex;
            flex-direction: column;
        }
        #map {
            flex-grow: 1;
            height: 100%;
            border-radius: 10px;
            overflow: hidden;
        }
    </style>
</head>
<body>
    <div id="sidebar">
        <h2>Positions</h2>
        <div id="positions-list"></div>
    </div>
    <div id="map-container">
        <div id="map"></div>
    </div>
    <script>
        var positions = JSON.parse({{.}});

        var map = L.map('map').setView([48.8566, 2.3522], 3);
        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
            attribution: '&copy; OpenStreetMap contributors'
        }).addTo(map);

        var positionList = document.getElementById("positions-list");

		positions.forEach(function(pos) {
			var formattedDate = new Date(Date.parse(pos.timestamp)).toLocaleString();

			var lat = pos.latitude || "N/A";
			var lng = pos.longitude || "N/A";

			var marker = L.marker([lat, lng]).addTo(map)
				.bindPopup('<b>' + formattedDate + '</b><br>Latitude: ' + lat + '<br>Longitude: ' + lng);

			var positionItem = document.createElement("div");
			positionItem.className = "position";
			positionItem.innerHTML = "<strong>" + formattedDate + "</strong><br>Lat: " + lat + ", Lng: " + lng;
			
			positionItem.onclick = function() {
				map.setView([lat, lng], 8);
				marker.openPopup();
			};

			positionList.appendChild(positionItem);
		});
    </script>
</body>
</html>`

	tmplParsed, err := template.New("map").Parse(tmpl)
	if err != nil {
		http.Error(w, "Template error", http.StatusInternalServerError)
		return
	}

	tmplParsed.Execute(w, template.JS(strconv.Quote(string(positionsJSON))))
}
