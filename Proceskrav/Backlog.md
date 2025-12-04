**BackLog:**
1. Trilateration manager //initially comited
2. WifiSniffer  // initially comited
3. DataNodes - sends data to the pipeline. 
4. DataPipeline - Performs trilateration and sends data to the server.


5. WifiSniffer doesn't publish because it disconnects wifi.
6. Use the data from the nodes for Trilateration.
7. Send data to the server.

**ToDO**
This is a list of things we would do if we had the time to do it.
1. Split the connection in the MqttBase into a separate thing, so the MqttBased objects doesn't each have their own connection.
2. 