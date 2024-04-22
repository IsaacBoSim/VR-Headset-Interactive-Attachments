import serial
import time
import os

try:
    # Open serial connection
    serial_port = '/dev/cu.usbserial-0231CEB3'
    baud_rate = 115200
    with serial.Serial(serial_port, baud_rate, timeout=1) as ser:
        ser.flushInput()

        # Create a directory for saving data if it doesn't exist
        data_dir = 'sensor_data'
        os.makedirs(data_dir, exist_ok=True)

        # Generate timestamp for the file name
        timestamp = time.strftime("%Y%m%d-%H%M%S")

        # Define the CSV file name with timestamp
        filename = os.path.join(data_dir, f'sensor_data_{timestamp}.csv')

        with open(filename, 'w') as f:
            f.write('Timestamp (ms),Pressure (PSI),Trigger\n')
            while True:
                if ser.in_waiting > 0:
                    try:
                        line = ser.readline().decode('utf-8').strip()
                        timestamp, button = line.split(',')
                        f.write(f'{timestamp},{button}\n')
                        print(f'Data logged: {line}')
                    except ValueError:
                        if "Reset" in line:
                            print(f"Special Start Message: {line}")
                        else:
                            print(f"Message: {line}")

except serial.SerialException as e:
    print(f"Serial connection error: {e}")
