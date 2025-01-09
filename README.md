# **ClimateCheck IoT** 
## Overviews
ClimateCheck is my first IoT project at Khon Kaen University, developed between December 2022 and March 2023. It tracks temperature and humidity in a room, sending Line notifications when user-defined limits are exceeded. It helps detect fires by alerting users if the temperature surpasses 57°C. Data is stored in Google Sheets and can be analyzed in Looker Studio with daily summaries of average and peak temperatures.

## Technologies Used
- **IoT Device:** ESP32
- **Sensors:** DHT11
- **Data Storage:** Google Sheets 
- **Data Visualization:** Looker Studio

## Setup Instructions
1. Set up **ESP32** and connect the **DHT11** sensor.
2. Install libraries: DHT, Wi-Fi, Google Sheets API.
3. Set up **Google Sheets** and **Google Apps Script**.
4. Upload the code to the board.

> **Note:** Line Notify service has been discontinued, so an alternative notification service may be used for alerts.

## License
For educational use only. Modify and use the code freely.

## Contact
For feedback or inquiries, feel free to reach out via [pathanin.kht@gmail.com](pathanin.kht@gmail.com).
