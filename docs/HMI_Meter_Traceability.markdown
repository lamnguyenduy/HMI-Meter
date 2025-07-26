# Traceability Matrix for HMI Meter System

## 1. Purpose
This document provides traceability between the Data Flow Diagram (DFD) and the Software Requirement Specification (SRS) for the HMI Meter system, ensuring all requirements are addressed in the design. It complies with ASPICE SYS.2, SWE.1, SWE.2, and ISO 26262 ASIL-A.

## 2. Traceability Matrix

| SRS ID | Requirement Description | DFD Component/Data Flow | Notes |
|--------|-------------------------|-------------------------|-------|
| **FUN-001** | Display vehicle speed (0–200 km/h, updated <100ms). | - **VehicleData**: Reads and validates speed data from Data Source (Raw Data).<br>- **HMIController**: Fetches speed from VehicleData (Validated Data), sends to HMIDisplay every 100ms.<br>- **HMIDisplay**: Displays speed on the interface (Display Data).<br>- **TFT Display**: Renders speed (Rendered Interface). | - Speed displayed as digital number (48px font).<br>- Response time <100ms ensured by QTimer. |
| **FUN-002** | Display fuel level (0–100%, warning <10%). | - **VehicleData**: Reads fuel data, checks <10% threshold (Raw Data → Validated Data).<br>- **HMIController**: Processes low fuel warning, sends to HMIDisplay.<br>- **HMIDisplay**: Displays fuel bar and yellow warning icon.<br>- **TFT Display**: Renders bar and icon. | - Horizontal bar (QProgressBar, 130x20px).<br>- Yellow warning (#FFCA28) when <10%. |
| **FUN-003** | Display engine temperature (0–150°C, warning >120°C). | - **VehicleData**: Reads temperature data, checks >120°C threshold.<br>- **HMIController**: Processes high temperature warning, sends to HMIDisplay.<br>- **HMIDisplay**: Displays temperature bar and red warning icon.<br>- **TFT Display**: Renders bar and icon. | - Horizontal bar (QProgressBar, 130x20px).<br>- Red warning (#F44336) when >120°C. |
| **FUN-004** | Display engine fault warning (boolean). | - **VehicleData**: Reads engine fault data (Raw Data).<br>- **HMIController**: Sends fault status to HMIDisplay.<br>- **HMIDisplay**: Displays red warning icon.<br>- **TFT Display**: Renders icon. | - Icon 32x32px, red (#F44336). |
| **NFUN-001** | User-friendly interface (font ≥16px, high contrast). | - **HMIDisplay**: Uses Arial font ≥16px, white/blue on black background.<br>- **TFT Display**: Renders 800x480px interface. | - Speed font 48px, labels 16–20px.<br>- Black background (#0F1017), white text (#FFFFFF). |
| **NFUN-002** | Interface response time <100ms. | - **HMIController**: Updates data every 100ms using QTimer.<br>- **HMIDisplay**: Processes Display Data efficiently.<br>- **TFT Display**: Renders without lag. | - Performance measured by Qt Creator profiling.<br>- CPU/RAM usage <50% (Windows Task Manager). |
| **NFUN-003** | Optimized for 7-inch TFT display (800x480). | - **HMIDisplay**: Layout with speed occupying 50%, compact fuel/temp bars.<br>- **TFT Display**: Renders at 800x480px resolution. | - Interface tested in Qt Creator (QSize(800, 480)). |

## 3. References
- SRS: `docs/HMI_Meter_SRS.md`
- DFD: `docs/HMI_Meter_DFD.png`
- SDD: `docs/HMI_Meter_SDD.md`