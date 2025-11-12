class LamportClock:
    def __init__(self):
        self.timestamp = 0

    def increment(self):
        self.timestamp += 1
        return self.timestamp

    def update(self, recTimestamp):
        self.timestamp = max(self.timestamp, recTimestamp) + 1
        return self.timestamp


class Process:
    def __init__(self, processId):
        self.processId = processId
        self.clock = LamportClock()

    def sendMessage(self, otherProcess):
        timestamp = self.clock.increment()
        print(f"\nProcess {self.processId} sends message with timestamp: {timestamp}")
        otherProcess.recMessage(timestamp)

    def recMessage(self, timestamp):
        newTimestamp = self.clock.update(timestamp)
        print(
            f"Process {self.processId} receives message with timestamp: {timestamp}. "
            f"Updated clock: {newTimestamp}"
        )


# Create 3 processes
processes = {i: Process(i) for i in range(1, 4)}


def menu():
    print("\nMenu:")
    print("1. Send a message")
    print("2. Exit")


def processChoice():
    try:
        choice = int(input("\nEnter the process number (1-3): "))
        if choice in processes:
            return processes[choice]
        else:
            print("Invalid choice, try again.")
            return processChoice()
    except ValueError:
        print("INVALID INPUT!!")
        return processChoice()


def main():
    while True:
        menu()
        choice = input("\nCHOOSE OPTION: ")

        if choice == '1':
            print("\n--- Message sender ---")
            curProcess = processChoice()
            print(f"Process {curProcess.processId} is ready.")

            print("\n--- Message receiver ---")
            targetProcess = processChoice()

            curProcess.sendMessage(targetProcess)

        elif choice == '2':
            print("Exiting.... :)")
            break

        else:
            print("Invalid option!!")


if __name__ == "__main__":
    main()
