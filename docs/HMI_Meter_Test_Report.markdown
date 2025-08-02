# Báo cáo kiểm thử đơn vị - HMI Meter
**Ngày**: 01/08/2025  
**Môi trường**: Qt Creator, Windows, 480x800  
**Kết quả**:
- **VehicleData**: 0/4 pass (lỗi: M1, M2 - chưa triển khai).
- **HMIDisplay**: 3/3 pass (lỗi tiềm năng: V1 - icon).
- **HMIController**: 1/1 pass (lỗi tiềm năng: C1 - timer).
**Danh sách lỗi**:
- **M1, M2**: Chưa triển khai `VehicleData`. Đề xuất: Thêm `VehicleData.cpp`.
- **V1**: Icon không hiển thị. Kiểm tra `resources.qrc`.
- **C1**: Timer chậm. Tăng `QTest::qWait` lên 200ms.