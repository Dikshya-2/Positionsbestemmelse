# Report: Positioning devices without GPS coverage

**Authors:** Dikshya, Jonas & Tatiana

**Date:** 2025-12-04 

## Abstract
This report describes a small indoor positioning system made with ESP32 IoT nodes that detect nearby devices and estimate their position without GPS. The system collects Wi-Fi RSSI measurements from multiple nodes, sends them to a local MQTT server, and uses a simple trilateration method to calculate approximate (x, y) coordinates. Tests at known locations showed that the system can detect devices and provide rough position estimates, though accuracy is limited by indoor signal noise and MAC address randomisation. The report also summarises key GDPR considerations, including the handling of MAC addresses as personal data.

## Introduction
Indoor positioning is challenging because GPS signals are unreliable or unavailable inside buildings. Many applications—such as monitoring device presence, occupancy, or asset tracking—require knowing a device’s location even without GPS.

The problem addressed in this project is how to estimate the position of mobile devices indoors using only local Wi-Fi signals. Challenges include signal variability, multipath effects, limited ESP32 memory, and MAC address randomisation, which can affect detection and data collection.

The objective of this project is to build a simple IoT system using multiple ESP32 nodes that can detect nearby devices, collect signal data, and estimate their approximate (x, y) position. The system also considers privacy and GDPR implications, ensuring that data collection minimises personal information while remaining functional.

## System Architecture

High-level overview of the system components and data flow.

## Hardware & Software

Description of the physical build and software stack.

## Data Collection

**Captured Data**

The ESP32 nodes capture the following information for each detected Wi-Fi signal:

1.  **NodeID** – Identifies the specific ESP32 node collecting the data.
    
2.  **Device ID / MAC** – Identifies the detected device sending the Wi-Fi probe. This is personal data under GDPR.
    
3.  **Timestamp** – Records when the packet was captured, enabling temporal correlation between nodes.
    
4.  **RSSI (Received Signal Strength Indicator)** – Measures signal strength of the detected device; crucial for estimating distances in trilateration.
    
5.  **Payload / Additional Data** – Contains numeric readings or counters sent by the device, used for monitoring and debugging.
    
6.  **Position (x, y)** – Calculated in the pipeline after trilateration, representing the estimated location of the detected device.
    

### Why It Matters

*   **RSSI values** are directly used to estimate distances between nodes and target devices, which is fundamental for trilateration.
    
*   **Timestamps** allow synchronization of measurements across multiple nodes to accurately reconstruct movement and location.
    
*   **NodeID and Device ID** ensure that measurements can be traced back to specific nodes and devices while maintaining privacy via hashing.
    
*   **Payload** provides additional context for testing, debugging, or validating signal data.
    
*   **Position** is the main output for the system, used for evaluating trilateration accuracy.
    

Capturing these fields ensures that the system has all the necessary information to calculate positions, analyze signal behavior, and debug issues effectively.

### How Calibration Was Performed

1.  **JSON Formatting & Validation:**
    
    *   Data is serialized into JSON for consistent structure and deserialized at the pipeline.
        
    *   Malformed messages are detected and discarded, ensuring only valid data is used.
        
2.  **RSSI Calibration:**
    
    *   RSSI values were compared against known distances under controlled conditions to establish a mapping from signal strength to distance.
        
    *   Calibration curves or reference measurements were used to correct for environmental factors like interference or signal attenuation.
        
3.  **Pipeline Testing:**
    
    *   Received JSON messages are processed in the pipeline, and positions are calculated using trilateration algorithms.
        
    *   Comparison with ground truth or known node positions allows verification and adjustment of calculations.
        
4.  **Memory and Processing Considerations:**
    
    *   Payload size and message frequency were optimized to prevent ESP32 crashes, ensuring consistent and reliable data capture during calibration tests.

## Positioning Method


**Trilateration Mathematics**

Using the distances d₀, d₁, d₂ to three known anchor nodes at positions (x₀, y₀), (x₁, y₁), (x₂, y₂), the estimated device position (x, y) is calculated by solving the system of equations:

>(x - xᵢ)² + (y - yᵢ)² = dᵢ², i = 0, 1, 2

This can be solved using a linearized least-squares approach, yielding:

>x = (CE - BF) / (AE - BD)y = (AF - CD) / (AE - BD)

#### Matrix Coefficients:

>A = 2(x₁ - x₀)B = 2(y₁ - y₀)C = d₀² - d₁² - x₀² + x₁² - y₀² + y₁²
>
>D = 2(x₂ - x₀)E = 2(y₂ - y₀)F = d₀² - d₂² - x₀² + x₂² - y₀² + y₂²

**Output:** The system returns the estimated (x, y) coordinates of the device, which can be visualised as a heatmap or used for further analysis.

The chosen positioning approach and the mathematical formulation.

## Privacy & GDPR

This project collects data from nearby wireless devices (Wi-Fi probes). Because some of this data relates to individuals, we evaluate it under **GDPR**.

### What data is personal?

- **MAC** addresses are personal data because they identify a device used by a person.

- **RSSI**, timestamp, and node position are not personal on their own, but become personal when linked to a **MAC** address.

> **_Conclusion:_** 
**MAC** = personal data.
**MAC** + **RSSI**/time/location = personal movement data.
---

### Is the data sensitive?

No. **MAC** addresses are ordinary personal data, not sensitive categories (health, biometrics, religion, etc.).

### When is the data personal?

- Static MACs → clearly personal.
- Randomized MACs → still personal, but lower identification risk.

In practice: MACs are treated as personal data at all times.

### Does combining **MAC** + time + place enrich the data?

Yes. Adding timestamps and node positions creates movement patterns, such as:

- Visits
- Duration of stay
- Repeated presence
- Devices moving together

This increases the responsibility for proper handling.

### Impact on data responsibility

Because movement patterns can relate to individuals, we must:

- limit what we collect
- avoid identification
- delete data quickly
- pseudonymize/anonymize whenever possible

## How we minimize data (**GDPR** compliance)
>
> **1. No raw MAC addresses stored**
> - MACs are hashed (e.g., **SHA**-**256** + salt) before storage.
>
> **2. Only necessary data collected We store only:**
>
> - hashed MAC
> - RSSI
> - timestamp
> - node ID
>
> We do not store: device type, manufacturer (**OUI**), full history, or other network details.
>
> **3. Short retention.**
> - Data is kept only for tests (e.g., 24–48 hours) or in memory.
>
>**4. No identification attempts.**
> - We never try to link devices to real people.
>
> 5. **Used only for the project purpose.**
> Data is used solely for:
> - position estimation
> - signal analysis
> - accuracy testing
>
>### Overall assessment.
>
>The project processes personal data (**MAC** addresses and derived movement information). It is not sensitive, but still protected. We reduce risk through hashing, minimal data collection, short retention, and strict purpose limitation. This aligns with the **GDPR** principles of dataminimization, purpose limitation, and risk reduction.
>
>
## Experiments & Results

Test setup, quantitative results, and visualizations.

## Discussion

Critical assessment of limitations and proposed improvements.

## Conclusion

Summary of achievements and lessons learned.

## References

>**Technical / IoT Resources**
>
>- ESP32 official documentation (Arduino / ESP-IDF)
>- MQTT protocol documentation (Mosquitto)
>- Wi-Fi Sniffer Examples:
>- Demo of Wi-Fi sniffer using generative AI (Claude): demo_kode/Proximity sniffer
>   - GitHub: IndoorPos_opgave_noter
>   - GitHub: ESP32 Sniffer by ETS-PoliTO
>- MQTT Server:
>   - Local MQTT server set up in the teaching lab
>   - Optionally, personal/local MQTT server can be used during development
>
>**GDPR Regulation (EU 2016/679)**
>
>- Article 4(1) – Definition of personal data
>- Article 4(5) – Pseudonymisation
>- Article 5 – Data minimisation, purpose limitation, storage limitation
>- Article 9 – Special categories of data
>- Article 25 – Data Protection by Design and by Default
>- Recital 26 – Identifiability and data combination
>- Recital 30 – Online identifiers (e.g., MAC and IP addresses)
>
>**Danish Data Protection Authority (Datatilsynet)**
>
>- Guidance on logging, IP addresses and identifiers (confirming that IP and MAC addresses are personal data)
>- Statements on location data as personal data
>
>**European Data Protection Board (EDPB)**
>
>- Guidelines on online identifiers (MAC addresses, device IDs, cookies)
>
>**Article 29 Working Party (WP29)**
>
>- Opinion 05/2014 on Anonymisation Techniques (hashing = pseudonymisation, not anonymisation)
>- Opinions on online identifiers as personal data

## Appendices

Additional material such as code snippets and extended tables.