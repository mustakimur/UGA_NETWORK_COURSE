from scapy.all import DNS, DNSQR, IP, UDP, sr1
import base64
import dns.message


def send_dns_query():
    dns_q = DNS(id=12345, qd=DNSQR(qtype='A', qname='google.com.'))
    ip = IP(dst='8.8.8.8')/UDP(sport=54321, dport=53)/dns_q
    dns_resp = sr1(ip)
    print(dns_resp.show())


def create_and_show_dns_request():
    dns_req = DNS(rd=1, qd=DNSQR(qname='www.example.com'))
    b = bytes(dns_req)
    p = DNS(b)
    p.show()
    
    #msg = b'\x00\x00\x01\x00\x00\x01\x00\x00\x00\x00\x00\x00\x03abc\x07example\x03net\x00\x00\x01\x00\x01'
    #DNS(msg).show()

def base64_dns():
    # Create DNS query for example.com, type A
    q = dns.message.make_query('example.com', 'A')

    # Convert to wire format (binary)
    wire = q.to_wire()

    # Base64 encode (URL-safe, without padding)
    encoded = base64.urlsafe_b64encode(wire).rstrip(b'=').decode()

    print(encoded)

def decode_raw():
    # Load the raw DNS response
    with open('response.bin', 'rb') as f:
        response_data = f.read()

    # Parse DNS message directly from wire format
    dns_response = dns.message.from_wire(response_data)

    # Print readable DNS response
    print(dns_response)



def main():
    print ("DNS Query:")
    send_dns_query()
    
    print("Create and show DNS request:")
    create_and_show_dns_request()
    
    print("Base64 DNS:")
    base64_dns()
    
    print("Decode raw:")
    # curl -s -H 'accept: application/dns-message' "https://dns.google/dns-query?dns=AAABAAABAAAAAAAAB2V4YW1wbGUDY29tAAABAAE" --output response.bin
    decode_raw()
    

if __name__ == '__main__':
    main()