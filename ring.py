import random
import time

print('Enter total processes')
n = int(input())

processes = []

print("Enter the processes in ring order:")
for i in range(n):
    processes.append(int(input()))

failedNode = max(processes)
aliveProcesses = [p for p in processes if p != failedNode]
detectFailureNode = random.choice(aliveProcesses)

print(f"\nThe process {failedNode} has failed")
print(f"Process {detectFailureNode} has detected failure of process {failedNode}\n")

currentIndex = processes.index(detectFailureNode)
electionMessage = [detectFailureNode]

print(f"Process {detectFailureNode} initiates election and sends message to next process.\n")

while True:
    currentIndex = (currentIndex + 1) % n
    currentProcess = processes[currentIndex]

    if currentProcess == failedNode:
        print(f"Process {currentProcess} has failed, skipping.")
        continue

    print(f"Process {currentProcess} received election message with IDs {electionMessage}")
    time.sleep(1)

    if currentProcess not in electionMessage:
        electionMessage.append(currentProcess)

    if currentProcess == detectFailureNode:
        print(f"\nElection message returned to initiator {detectFailureNode} with IDs: {electionMessage}")
        break

leader = max(electionMessage)
print(f"\nThe new coordinator is: {leader}")