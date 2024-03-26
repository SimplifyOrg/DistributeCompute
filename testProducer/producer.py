import pika
import time
import random
import json

connection_parameters = pika.ConnectionParameters('localhost')

connection = pika.BlockingConnection(connection_parameters)

channel = connection.channel()

# channel.queue_declare(queue='queue-name')
# channel.exchange_declare(exchange='exch-name')
# channel.queue_bind(
    # exchange='exch-name', queue='queue-name', routing_key='routingkey')

messageId = 1

while(True):
    #message = f"Sending Message Id: {messageId}"
    #messageJson = '{"Process" : "process", "downloadURL" : "https://raw.githubusercontent.com/lucasg/Dependencies/master/test/manifest-regress/SystemSettings.exe", "downloadLocation" : "{"linux" : "/home/abs/process/build/"}", "PathType" : "full-path", "Param" : "", "ResponseConfig" : {"QueueName" : "queue-name","ExchangeName" : "exch-name","Host" : "localhost","Port" : "5672","User" : "guest","Password" : "guest"} }'
    messageJson = '{"Process" : "SystemSettings", "downloadURL" : "https://raw.githubusercontent.com/SimplifyOrg/TestProcess/main/build/process", "downloadLocation" : "", "PathType" : "process-name", "Param" : "", "ResponseConfig" : {"QueueName" : "queue-name","ExchangeName" : "exch-name","Host" : "localhost","Port" : "5672","User" : "guest","Password" : "guest"} }'
    #message = json.dumps(messageJson)
    channel.basic_publish(exchange='exch-name', routing_key='routingkey', body=str(messageJson))

    print(f"sent message: {messageJson}")
    
    time.sleep(random.randint(1, 4))

    messageId+=1