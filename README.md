# **ClimateCheck IoT** 
## Project Status: No Longer Maintained
## Overviews
ClimateCheck is my first IoT project at Khon Kaen University, developed between December 2022 and March 2023. It tracks temperature and humidity in a room, sending Line notifications when user-defined limits are exceeded. It helps detect fires by alerting users if the temperature surpasses 57°C. Data is stored in Google Sheets and can be analyzed in Looker Studio with daily summaries of average and peak temperatures.

## Technologies Used
- **IoT Device:** ESP32
- **Sensors:** DHT11
- **Data Storage:** Google Sheets 
- **Data Visualization:** Looker Studio

## Example
### 1. Google Sheets 
![Google Sheets](https://github.com/pathanin-kht/ClimateCheck-IoT/blob/6d8e60c76a7cb1f824206968f3a5218bb822abc1/Example/Google%20Sheets.png)
### 2. Looker Studio
![Looker Studio](https://github.com/pathanin-kht/ClimateCheck-IoT/blob/6d8e60c76a7cb1f824206968f3a5218bb822abc1/Example/Looker%20Studio.png)
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
