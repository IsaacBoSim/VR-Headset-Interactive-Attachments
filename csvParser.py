import csv


def generate_arduino_code(csv_filename, output_filename):
    servo_controls = []
    last_time = 0
    servoList = ['servoRightEar', 'servoLeftEar']

    with open(csv_filename, 'r') as file:
        reader = csv.DictReader(file)
        reader.fieldnames = [name.strip() for name in reader.fieldnames]  # Strip spaces from field names

        print("Corrected field names:", reader.fieldnames)

        for row in reader:
            try:
                current_time = int(row['Timestamp (ms)'].strip())
                delay_time = current_time - last_time
                last_time = current_time
                button = int(row['Button'].strip())
                position = row['Position'].strip()
                message = row['Message'].strip()

                servo_controls.append((delay_time, button, position, message))
            except ValueError as ve:
                print(f"Error parsing row: {row} - {ve}")
                continue

    with open(output_filename, 'w') as file:
        file.write('#include <Servo.h>\n\n')
        file.write('Servo servoLeftEar, servoRightEar;\n\n')
        file.write('const int fanPin = 10; // Define the fan pin\n')
        file.write('const int startButton = 6; // Define the start button\n\n')
        file.write('void setup() {\n')
        file.write('  servoLeftEar.attach(7);\n')
        file.write('  servoRightEar.attach(8);\n')
        file.write('  pinMode(fanPin, OUTPUT);\n')
        file.write('  pinMode(startButton, INPUT);\n')
        file.write('  digitalWrite(fanPin, LOW);\n')

        file.write('}\n\n')
        file.write('void loop() {\n')
        file.write('  while (digitalRead(startButton) == LOW) { //wait for start button\n')
        file.write('    if (digitalRead(startButton) == HIGH){\n')
        file.write('      Serial.print("Starting Recording");\n')
        file.write('      break;\n')
        file.write('    }\n')
        file.write('  }\n')
        for delay_time, button, position, message in servo_controls:
            file.write(f'  delay({delay_time});\n')
            if "fan" in message:
                button = 'fanPin'
                file.write(f'  digitalWrite({button}, {position});\n')
            elif "servo" in message:
                button = str(servoList[button - 3])
                file.write(f'  {button}.write({position});\n')
            else:
                continue
        file.write('  end();\n')
        file.write('}\n\n')

        file.write('void end() {\n')
        file.write('  digitalWrite(fanPin, LOW);\n')
        file.write('  Serial.println("Ended Recording");\n')
        file.write('}\n')





# Example usage
generate_arduino_code('headset_data_20240425-154324.csv', 'generated_servo_sketch.ino')
