import serial
import matplotlib.pyplot as plt
import csv

f = open("ecg_data.csv", "r+")
writer = csv.writer(f)

serial_object = serial.Serial("COM10", 115200)

num_readings = 0

while i < 1000:
    try:
        reading = int(serial_object.readline().decode().strip())
        writer.writerow([reading])
        num_readings += 1
    except:
        print("Failed to read from serial port")

f.seek(0)

reader = csv.reader(f)

data = []

for dataline in reader:
    if len(dataline) > 0:
        var = int(dataline[0])
        data.append(var)
        if var > 160:
            count += 1

plt.plot(data)
plt.show()

print("The number of R peaks is", count)
print("The average interval of R peaks is", 60 / count)
