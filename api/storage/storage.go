package storage

import (
	"api/models"
	"database/sql"
	"fmt"

	_ "github.com/mattn/go-sqlite3"
)

var db *sql.DB

func InitDB(dbFilePath string) error {
	var err error
	db, err = sql.Open("sqlite3", dbFilePath)
	if err != nil {
		return fmt.Errorf("error opening database: %v", err)
	}

	_, err = db.Exec(`CREATE TABLE IF NOT EXISTS positions (
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
		latitude REAL NOT NULL,
		longitude REAL NOT NULL
	)`)
	if err != nil {
		return fmt.Errorf("error creating table: %v", err)
	}

	return nil
}

func SavePosition(pos models.Position) error {
	_, err := db.Exec("INSERT INTO positions (timestamp, latitude, longitude) VALUES (?, ?, ?)", pos.Timestamp, pos.Latitude, pos.Longitude)
	return err
}

func GetPositions() ([]models.Position, error) {
	rows, err := db.Query("SELECT timestamp, latitude, longitude FROM positions")
	if err != nil {
		return nil, err
	}
	defer rows.Close()

	var positions []models.Position
	for rows.Next() {
		var pos models.Position
		if err := rows.Scan(&pos.Timestamp, &pos.Latitude, &pos.Longitude); err != nil {
			return nil, err
		}
		positions = append(positions, pos)
	}
	return positions, nil
}
