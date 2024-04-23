import csv


def generate_arduino_code(csv_filename, output_filename):
    servo_controls = []
    last_time = 0
    servoList = ['servoNape', 'servoThroat', 'servoLeftEar', 'servoRightEar']

    with open(csv_filename, 'r') as file:
        reader = csv.DictReader(file)
        reader.fieldnames = [name.strip() for name in reader.fieldnames]  # Strip spaces from field names

        print("Corrected field names:", reader.fieldnames)

        for row in reader:
            try:
                current_time = int(row['Timestamp (ms)'].strip())
                delay_time = current_time - last_time
                last_time = current_time
                button = int(row['Button'].strip())+4
                position = row['Position'].strip()
                message = row['Message'].strip()

                servo_controls.append((delay_time, button, position, message))
            except ValueError as ve:
                print(f"Error parsing row: {row} - {ve}")
                continue

    with open(output_filename, 'w') as file:
        file.write('#include <Servo.h>\n\n')
        file.write('Servo servoNape, servoThroat, servoLeftEar, servoRightEar;\n\n')
        file.write('const int fanPin = 10; // Define the fan pin\n')
        file.write('void setup() {\n')
        file.write('  servoNape.attach(6);\n')
        #file.write('  servoThroat.attach(7);\n')
        file.write('  servoLeftEar.attach(8);\n')
        file.write('  servoRightEar.attach(9);\n')
        file.write('  pinMode(fanPin, OUTPUT);\n')
        file.write('}\n\n')
        file.write('void loop() {\n')

        for delay_time, button, position, message in servo_controls:
            file.write(f'  delay({delay_time});\n')
            if "fan" in message:
                file.write(f'  digitalWrite({button}, {position});\n')
            elif "servo" in message:
                button = str(servoList[button-6])
                file.write(f'  {button}.write({position});\n')
            else:
                continue


        file.write('  while(true); // Stop further actions\n')
        file.write('}\n')


# Example usage
generate_arduino_code('headset_data_20240422-203500.csv', 'generated_servo_sketch.ino')
