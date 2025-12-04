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

**Day 4: Send data to the server**
1. Queue Handling
- We have created a queue intended to push data, but the portfolio report has not been published yet.

2. Portfolio Report
   - GDPR
   - Introduction
   - Abstract

3. Discussion on Moving Forward
   - Our original idea was for each ESP32 node to act as both publisher and subscriber, publishing to a broker that would then forward data to another broker.
   - This design proved impractical due to complexity, potential message loops, and the limited memory and processing capacity of the ESP32 devices.

4. Proposed Solution:
   -  The simplest and most robust approach is to move the pipeline to a central computer, using a C# application to perform trilateration and process incoming data.
   -  ESP32 nodes act solely as publishers, sending data to separate topics that the computer subscribes to.
   -  This separates responsibilities, reduces load on the ESP32 devices, simplifies debugging, and ensures reliable, scalable data flow.

5. JSON Payload Issue
-  We noticed that some JSON messages were missing the closing bracket. This did not occur in every payload, and the cause is currently unknown.
