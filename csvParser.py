import csv

def generate_arduino_code(csv_filename, output_filename):
    servo_controls = []
    last_time = 0

    # Read the CSV file
    with open(csv_filename, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            current_time = int(row['timestamp'])
            delay_time = current_time - last_time
            last_time = current_time
            servo_controls.append((delay_time, row['servo'], row['position']))

    # Generate the Arduino code
    with open(output_filename, 'w') as file:
        file.write('#include <Servo.h>\n\n')
        file.write('Servo servoNape, servoThroat, servoLeftEar, servoRightEar;\n\n')
        file.write('void setup() {\n')
        file.write('  servoNape.attach(3);\n')
        file.write('  servoThroat.attach(5);\n')
        file.write('  servoLeftEar.attach(6);\n')
        file.write('  servoRightEar.attach(9);\n')
        file.write('}\n\n')
        file.write('void loop() {\n')

        for delay_time, servo, position in servo_controls:
            file.write(f'  delay({delay_time});\n')
            file.write(f'  {servo}.write({position});\n')

        file.write('  while(true); // Stop further actions\n')
        file.write('}\n')


# Example usage
generate_arduino_code('servo_timings.csv', 'generated_servo_sketch.ino')
