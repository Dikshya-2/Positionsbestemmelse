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

What data is captured, why it matters, and how calibration was performed.

## Positioning Method

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

- visits

- duration of stay

- repeated presence

- devices moving together

This increases the responsibility for proper handling.

### Impact on data responsibility

Because movement patterns can relate to individuals, we must:

- limit what we collect

- avoid identification

- delete data quickly

- pseudonymize/anonymize whenever possible

>## How we minimize data (**GDPR** compliance)
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