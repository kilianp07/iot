package main

import (
	"api/handlers"
	"api/storage"
	"fmt"
	"log"
	"net/http"
	"os"

	"github.com/spf13/cobra"
)

var rootCmd = &cobra.Command{
	Use:   "server",
	Short: "Start the API server",
	Run: func(cmd *cobra.Command, args []string) {
		port, _ := cmd.Flags().GetString("port")

		if port == "" {
			fmt.Println("Error: --port flag is required")
			cmd.Usage()
			os.Exit(1)
		}

		dbFilePath, _ := cmd.Flags().GetString("db")
		if dbFilePath == "" {
			fmt.Println("Error: --db flag is required")
			cmd.Usage()
		}

		if err := storage.InitDB(dbFilePath); err != nil {
			log.Fatalf("Error initializing database: %v", err)
		}
		http.HandleFunc("/position", handlers.PostPositionHandler)
		http.HandleFunc("/", handlers.MapHandler)

		log.Printf("Server running on :%s", port)
		log.Fatal(http.ListenAndServe(fmt.Sprintf(":%s", port), nil))

	},
}

func init() {
	rootCmd.Flags().StringP("port", "p", "", "Port for the server (mandatory)")
	rootCmd.Flags().StringP("db", "d", "", "Path to the sqlite database file (mandatory)")
}

func main() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
