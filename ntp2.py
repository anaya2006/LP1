import socket
import struct
import time

def get_ntp_time(host="pool.ntp.org"):
    port = 123
    buf = 1024
    address = (host, port)
    msg = b'\x1b' + 47 * b'\0'
    TIME1970 = 2208988800  # NTP epoch: 1900 to Unix epoch: 1970

    client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client.settimeout(5)

    try:
        t1 = time.time()  # client send time
        client.sendto(msg, address)
        msg, address = client.recvfrom(buf)
        t4 = time.time()  # client receive time
    except socket.timeout:
        print("No response from NTP server.")
        return None

    if msg:
        unpacked = struct.unpack('!12I', msg)
        # Extract server receive (t2) and transmit (t3) timestamps
        t2 = unpacked[8] + float(unpacked[9]) / 2**32
        t3 = unpacked[10] + float(unpacked[11]) / 2**32

        # Convert NTP time to Unix time
        t2 -= TIME1970
        t3 -= TIME1970

        # θ (offset) and δ (delay)
        theta = ((t2 - t1) + (t3 - t4)) / 2
        delta = (t4 - t1) - (t3 - t2)

        local_time = t4 + theta

        print("Delta:", delta)
        print("Theta:", theta)
        return local_time, theta, delta, t1, t2, t3, t4

    return None


if __name__ == "__main__":
    result = get_ntp_time()
    if result:
        local_time, offset, delay, t1, t2, t3, t4 = result

        print(f"\nAdjusted local time: {time.ctime(local_time)}")
        print(f"Offset: {offset:.6f} seconds")
        print(f"Round-trip delay: {delay:.6f} seconds\n")

        print("Raw timestamps:")
        print(f"t1 (client send time): {t1} ({time.ctime(t1)})")
        print(f"t2 (server recv time): {t2} ({time.ctime(t2)})")
        print(f"t3 (server transmit time): {t3} ({time.ctime(t3)})")
        print(f"t4 (client recv time): {t4} ({time.ctime(t4)})\n")

        print("Corrected timestamps (raw + offset):")
        print(f"t1 corrected: {t1 + offset} ({time.ctime(t1 + offset)})")
        print(f"t2 corrected: {t2 + offset} ({time.ctime(t2 + offset)})")
        print(f"t3 corrected: {t3 + offset} ({time.ctime(t3 + offset)})")
        print(f"t4 corrected: {t4 + offset} ({time.ctime(t4 + offset)})")
