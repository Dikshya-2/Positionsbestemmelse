**Dag 1: Teamwork**
1. Setup project in github
2. Copied Smiley project
3. Removed code we don't need in this project.
4. Writing the backlog.

**Day 2: Debugging WiFi Sniffer Publishing**
1. Tested the WiFi sniffer to confirm it captures packets correctly.  
2. Attempted to publish sniffer data to MQTT, but nothing was sent.  
3. Investigated why the ESP32 disconnects from WiFi whenever promiscuous mode is enabled.  
4. Checked callbacks, connection status, and MQTT behavior to identify the cause.  

**Day 3: Use the data from the nodes for Trilateration**
1. Previously attempted to use the device pipeline directly  
   - Identified issues in the pipeline that prevent proper data reception.

2. Using the broker directly instead of the pipeline
   - Consider configuring the pipeline to read from the broker.  
   - Aim to establish a reliable data flow from node devices through the broker to the pipeline.

3. Subscriber callback setup in MQTT
    - Set up a callback in the subscriber to receive data published by the nodes.  
   - Verified that the subscriber is correctly registered to the broker topic.  
   - Confirmed that the callback function successfully processes incoming messages for further use in trilateration.