#Implementing a MQTT broker using the Paho library 

import paho.mqtt.client as mqtt
import hashlib
import matplotlib.pyplot as plt
import base64
import sqlite3


broker_address = "mqtt.eclipseprojects.io" 
broker_port = 1883

client = mqtt.Client()

global data_dictionary
data_dictionary = {}

client.connect(broker_address, broker_port, 60)

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker with result code " + str(rc))
    client.subscribe("ecg_project")

def on_message(client, userdata, msg):
    # conn = sqlite3.connect('database.db')
    # c = conn.cursor()
    message = msg.payload.decode('utf-8')
    print(message)
    ### Message format: <team_name>:<data>
    try:
        message = message.split(":")
        team = message[0]
        data = message[1]

        if (team not in data_dictionary.keys()):
            data_dictionary[team] = [int(data)]
        else:
            if (len(data_dictionary[team]) > 500):
                data_dictionary[team] = [int(data)]
            else:
                data_dictionary[team].append(int(data))
        
    except:
        return

    # c.execute("SELECT * FROM users WHERE name=?", (user_name,))
    # user = c.fetchone()
    # if user == None:    
    #     c.execute("INSERT INTO users ('name') VALUES (?)", (user_name,))
    #     print("User does not exist, added to database.")
    #     user = c.lastrowid
    #     print("User: ", user)
    #     conn.commit()

    # c.execute("SELECT * FROM users WHERE name=?", (user_name,))
    # user = c.fetchone()
    # print("User: ", user)
    # data = ','.join(ecg_data)
    # c.execute('''INSERT INTO data (user_id, message, timestamp) VALUES (?, ?, ?)''', (user[0], data, timestamp))
    # conn.commit()


client.on_connect = on_connect
client.on_message = on_message
client.loop_start()
team_subplots = tuple([i for i in data_dictionary.keys()])
plt.ion()
plt.xlim(0, 500)


while True:
    try:
        for team in data_dictionary.keys():
            # print("Team: ", data_dictionary.keys().index(team) + 1)
            plt.subplot(4, 2, list(data_dictionary.keys()).index(team) + 1)
            plt.plot(data_dictionary[team])
            plt.title(str(team))
    except:
        print("Error", data_dictionary.keys())
    plt.draw()
    plt.pause(0.001)
    plt.clf()