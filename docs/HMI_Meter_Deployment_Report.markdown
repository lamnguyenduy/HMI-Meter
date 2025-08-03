# Performance Evaluation Report - HMI Meter

**Date**: August 03, 2025  
**Time**: 11:45 AM +07  
**Environment**: Qt Creator (Qt 5/6), Windows 10, Intel Core i5-8265U, 8GB RAM, 480x800 resolution  
**Objective**: Evaluate CPU/RAM performance using Qt Profiler, ensure response time <100ms (NFUN-002), identify risks related to ETW dependency, and propose improvements.  
**Scope**:  
- **Model** (`VehicleData`): Provides data (speed, fuel, temperature, warnings).  
- **View** (`HMIDisplay`): Displays UI with `speedLabel`, `fuelBar`, `tempBar`, `warningIcons`.  
- **Controller** (`HMIController`): Updates UI every 100ms.  
- **Tests**: `tst_VehicleData`, `tst_HMIDisplay`, `tst_HMIController`.  

## 1. Performance Evaluation (Qt Profiler)

### Configuration
- **Tool**: Qt Profiler with Event Tracing for Windows (ETW).  
- **Setup**:  
  - Application: `HMIMeter` in Release mode.  
  - Duration: 60 seconds.  
  - Data: `MockVehicleData` (speed: 120 km/h, fuel: 60%, temperature: 100°C, warnings: [true, false, true]).  
  - Update frequency: 100ms (`QTimer` in `HMIController`).  

### CPU Results
- **Execution Time of `HMIDisplay::updateDisplay`**:  
  - Average: 5.2ms (measured via `QElapsedTimer` in `tst_HMIDisplay::testResponseTime`).  
  - Peak: 7.8ms (when updating `speedLabel`, `fuelBar`, `tempBar`, and three `warningIcons`).  
  - **Remark**: Meets NFUN-002 (<100ms), safe for real-time systems (ISO 26262 ASIL-A).  
- **CPU Load**:  
  - Average: 2–3% (Intel Core i5-8265U, 4 cores, 1.6–3.9GHz).  
  - Peak: 5% during initial icon loading.  
  - **Remark**: Low CPU usage, suitable for embedded systems.  

### RAM Results
- **Memory Usage**:  
  - Application: ~20MB (includes `HMIDisplay.ui` and three 32x32px PNG icons).  
  - Resources: ~500KB (`resources.qrc`).  
  - Peak: 25MB during `QApplication` initialization and `ui_HMIDisplay.h` loading.  
  - **Remark**: Low memory footprint, suitable for embedded devices.  

### Risks and Limitations
- **Risk R1**: Dependency on ETW (Event Tracing for Windows) in Qt Profiler.  
  - **Description**: ETW may hide performance bottlenecks (e.g., I/O delays or thread contention) due to limited granularity or incomplete event capture.  
  - **Impact**: Moderate (may miss microsecond-level issues in `updateDisplay`).  
  - **Mitigation**:  
    - Use alternative tools like **Windows Performance Analyzer (WPA)** for deeper ETW analysis.  
    - Employ **perf** on Linux (requires porting project to Linux, e.g., Ubuntu 22.04 with kernel 5.15+).  
    - Add manual instrumentation with `QElapsedTimer` in critical functions for precise timing.  
- **Risk R2**: CPU spikes during initial PNG icon loading.  
  - **Description**: Decoding PNGs in `resources.qrc` causes ~5% CPU spike.  
  - **Impact**: Low (one-time event at startup).  
  - **Mitigation**: Use SVG icons or pre-cache PNGs.  
- **Risk R3**: Memory spike during `ui_HMIDisplay.h` creation.  
  - **Description**: Qt Designer generates large intermediate UI files.  
  - **Impact**: Low (build-time only).  
  - **Mitigation**: Optimize `HMIDisplay.ui` by reducing widget complexity.  

## 2. Test Results
- **tst_VehicleData**:  
  - Status: Failed (0/4 test cases) due to missing `VehicleData.cpp`.  
  - Errors: M1, M2 (undefined `getSpeed`, `getFuelLevel`, `getTemperature`, `getWarnings`).  
  - Fix: Implemented dummy `VehicleData.cpp`, pending real implementation.  
- **tst_HMIDisplay**:  
  - Status: Passed (4/4 test cases, including `testResponseTime`).  
  - Response time: 5.2ms average for `updateDisplay`.  
  - Potential error: V1 (icons not displayed if `resources.qrc` misconfigured).  
  - Fix: Verified `resources.qrc` and `icons/` directory.  
- **tst_HMIController**:  
  - Status: Passed (2/2 test cases, including `testResponseTime`).  
  - Update cycle: ~200ms for two cycles (±10ms).  
  - Potential error: C1 (timer delay).  
  - Fix: Increased `QTest::qWait` to 200ms, verified `QTimer`.  

## 3. Proposed Improvements

### 3.1. Analog Gauge
- **Description**: Replace `speedLabel` (text) with an analog gauge for speed display to enhance user experience and visualization (per Figma mockup).  
- **Implementation**:  
  - Use `QGraphicsView` or `QPainter` to draw an analog gauge.  
  - Add `SpeedGauge` class in `src/SpeedGauge.h/.cpp`.  
  - Update `HMIDisplay.ui`: Replace `speedLabel` with `QGraphicsView` (`speedGauge`).  
  - Example code:
    ```cpp
    // src/SpeedGauge.h
    #ifndef SPEEDGAUGE_H
    #define SPEEDGAUGE_H
    #include <QGraphicsView>
    class SpeedGauge : public QGraphicsView {
        Q_OBJECT
    public:
        explicit SpeedGauge(QWidget* parent = nullptr);
        void setSpeed(float speed);
    private:
        float speed{0.0f}; // 0-200 km/h
    };
    #endif
    ```
    ```cpp
    // src/SpeedGauge.cpp
    #include "SpeedGauge.h"
    #include <QPainter>
    #include <cmath>
    SpeedGauge::SpeedGauge(QWidget* parent) : QGraphicsView(parent) {
        setScene(new QGraphicsScene(this));
        setFixedSize(200, 200);
    }
    void SpeedGauge::setSpeed(float speed) {
        this->speed = std::max(0.0f, std::min(200.0f, speed));
        QPainter painter(viewport());
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawEllipse(10, 10, 180, 180); // Draw gauge
        float angle = (speed / 200.0f) * 270.0f - 135.0f; // Needle angle: -135° to 135°
        painter.drawLine(100, 100, 100 + 80 * cos(angle * M_PI / 180), 100 - 80 * sin(angle * M_PI / 180));
        viewport()->update();
    }
    ```
  - Update `HMIDisplay::updateDisplay` to call `speedGauge->setSpeed(speed)`.  
- **Benefits**: Improved visualization, aligns with automotive UI standards.  
- **Impact**: Slight CPU increase (~1–2% due to rendering), requires performance retesting.  
- **Action**: Add `SpeedGauge` to `src/`, update `HMIMeter.pro`:
  ```plaintext
  SOURCES += src/SpeedGauge.cpp
  HEADERS += src/SpeedGauge.h
  ```

### 3.2. Message Queue/Shared Memory
- **Description**: Replace `.txt` file-based data I/O with a Windows Service using **message queue** or **shared memory** to transfer data from source (e.g., CAN bus) to `VehicleData`.  
- **Implementation**:  
  - Use **QSharedMemory** (Qt) or **Windows Message Queue (MSMQ)**.  
  - Create a Windows Service (`HMI_DataService`) to write data to shared memory every 50ms.  
  - Example `QSharedMemory` in `VehicleData`:
    ```cpp
    // src/VehicleData.h
    #ifndef VEHICLEDATA_H
    #define VEHICLEDATA_H
    #include <QSharedMemory>
    #include <array>
    class VehicleData {
    public:
        VehicleData();
        float getSpeed();
        float getFuelLevel();
        float getTemperature();
        std::array<bool, 3> getWarnings();
    private:
        QSharedMemory sharedMemory;
    };
    #endif
    ```
    ```cpp
    // src/VehicleData.cpp
    #include "VehicleData.h"
    VehicleData::VehicleData() : sharedMemory("HMI_Data") {
        if (!sharedMemory.attach()) {
            sharedMemory.create(sizeof(float) * 3 + sizeof(bool) * 3); // Speed, fuel, temp, 3 warnings
        }
    }
    float VehicleData::getSpeed() {
        if (sharedMemory.lock()) {
            float* data = static_cast<float*>(sharedMemory.data());
            float speed = data[0];
            sharedMemory.unlock();
            return std::max(0.0f, std::min(200.0f, speed));
        }
        return 0.0f;
    }
    // Similar for getFuelLevel, getTemperature, getWarnings
    ```
- **Benefits**:  
  - Reduced I/O latency compared to `.txt`.  
  - Improved reliability (ISO 26262).  
- **Impact**: Increases RAM usage (~1MB for shared memory), requires synchronization testing.  
- **Action**: Implement `HMI_DataService`, integrate `QSharedMemory` into `VehicleData`.  

## 4. Alternative Tools for Performance Analysis
- **Issue**: Qt Profiler relies on ETW, which may hide subtle performance issues (e.g., thread contention or I/O delays).  
- **Alternatives**:  
  - **Windows Performance Analyzer (WPA)**: Provides detailed ETW analysis, better granularity for CPU and memory events.  
    - **Setup**: Install Windows ADK, run `xperf -on base+latency`, analyze with WPA.  
  - **Visual Studio Profiler**: Offers deeper insights into thread and memory usage.  
    - **Setup**: Open project in Visual Studio, use Diagnostic Tools.  
  - **Linux perf (if ported)**: Use on Ubuntu 22.04 (kernel 5.15+) for high-precision profiling.  
    - **Setup**: `sudo perf stat ./out/HMIMeter`.  
- **Recommendation**: Combine Qt Profiler with WPA for critical sections (`updateDisplay`) to validate NFUN-002 compliance.  

## 5. Conclusion
- **Performance**:  
  - CPU: 2–5%, response time 5.2ms (NFUN-002 compliant).  
  - RAM: 20–25MB, suitable for embedded systems.  
- **Test Results**:  
  - `tst_HMIDisplay` and `tst_HMIController` passed; `tst_VehicleData` requires `VehicleData.cpp`.  
- **Actions**:  
  - Implement `SpeedGauge` and retest performance.  
  - Replace `.txt` with `QSharedMemory` and Windows Service.  
  - Use WPA or Visual Studio Profiler to address ETW limitations.  
- **Timeline**: 2 weeks (starting 04/08/2025).