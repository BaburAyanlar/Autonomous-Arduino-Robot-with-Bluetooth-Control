import bluetooth as bt
print "Searching for devices..."
print ""
nearby_devices = bt.discover_devices()
#Run through all the devices found and list their name
num = 0
print "Select your device by entering its coresponding number..."
for i in nearby_devices:
	num+=1
	print num , ": " , bt.lookup_name( i )

selection = input("> ") - 1
print "You have selected", bluetooth.lookup_name(nearby_devices[selection])
bd_addr = nearby_devices[selection]

port = 1

print "Generating Socket..."
sock = bt.BluetoothSocket(RFCOMM)
sock.connect((bd_addr,port))
while True:
	command = input("> Enter command to be sent to the robot...")
	sock.send(command)
