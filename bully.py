import random
import time

print('Enter total processes')
n = int(input())

processes = []

print("Enter the processes:")
for i in range(n):
    processes.append(int(input()))

failedNode = max(processes)
detectFailureNode = random.choice([p for p in processes if p != failedNode])

print(f"\nThe process {failedNode} has failed")
print(f"Process {detectFailureNode} has detected failure of process {failedNode}\n")

# Start election from the detecting process
currentInitiator = detectFailureNode
flag = False
leader = -1

while True:
    higherProcesses = []
    for p in processes:
        if p != failedNode and p > currentInitiator:
            higherProcesses.append(p)

    if not higherProcesses:
        leader = currentInitiator
        break
    else:
        print(f"Process {currentInitiator} sends election message to:", higherProcesses)
        time.sleep(1)
        print(f"Processes {higherProcesses} respond with OK\n")
        time.sleep(1)
        currentInitiator = min(higherProcesses)

print(f"\nThe new coordinator is: {leader}")