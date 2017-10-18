# slidingwindow
-----------------
TUBES JARKOM 1

**Petunjuk penggunaan program.**
1. Buka terminal.
2. Masuk ke folder ini.
3. Ketik "Make" lalu tekan enter.
4. Ketik "./sendFile <filename> <windowsize> <buffersize> <destination_ip> <destination_port>" lalu tekan enter untuk mengirimkan data pada filename ke destination_ip melalui destination_port.
5. Ketik "./recvfile <filename> <windowsize> <buffersize> <port>" lalu tekan enter untuk menerima file melalui port lalu menyimpannya pada filename.

**Cara kerja program sliding window.**
1. 

**Pembagian tugas.**


**Pertanyaan:**
1.	Apa yang terjadi jika advertised window yang dikirim bernilai 0? Apa cara untuk menangani hal tersebut?
Jawab: 
Jika advertised window yang dikirim bernilai 0, maka data tidak bisa dikirim. Receiver akan menunggu sender untuk kembali mengirimkan data tersebut.

titip referensi (dari buku peterson):
An advertised window of 0 means that the sending side cannot
transmit any data, even though data it has previously sent has been successfully ac-
knowledged. Finally, not being able to transmit any data means that the send buffer
fills up, which ultimately causes TCP to block the sending process. As soon as the
receiving process starts to read data again, the receive-side TCP is able to open its win-
dow back up, which allows the send-side TCP to transmit data out of its buffer. When
this data is eventually acknowledged, LastByteAcked is incremented, the buffer space
holding this acknowledged data becomes free, and the sending process is unblocked
and allowed to proceed.
There is only one remaining detail that must be resolved—how does the sending
side know that the advertised window is no longer 0? As mentioned above, TCP always
sends a segment in response to a received data segment, and this response contains the
latest values for the Acknowledge and AdvertisedWindow fields, even if these values
have not changed since the last time they were sent. The problem is this. Once the
receive side has advertised a window size of 0, the sender is not permitted to send
any more data, which means it has no way to discover that the advertised window
is no longer 0 at some time in the future. TCP on the receive side does not sponta-
neously send nondata segments; it only sends them in response to an arriving data
segment.
TCP deals with this situation as follows. Whenever the other side advertises a
window size of 0, the sending side persists in sending a segment with 1 byte of data
every so often. It knows that this data will probably not be accepted, but it tries
anyway, because each of these 1-byte segments triggers a response that contains the
current advertised window. Eventually, one of these 1-byte probes triggers a response
that reports a nonzero advertised window.


2.	Sebutkan field data yang terdapat TCP Header serta ukurannya, ilustrasikan, dan jelaskan kegunaan dari masing-masing field data tersebut!
Jawab:
	0                   1                   2                   3
	0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|          Source Port          |       Destination Port        |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|                        Sequence Number                        |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|                    Acknowledgment Number                      |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|  Data |           |U|A|P|R|S|F|                               |
	| Offset| Reserved  |R|C|S|S|Y|I|            Window             |
	|       |           |G|K|H|T|N|N|                               |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|           Checksum            |         Urgent Pointer        |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|                    Options                    |    Padding    |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|                             data                              |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Source Port: 16 bits
   Menunjukkan nilai port number di node asal.

   Destination Port: 16 bits
   Menunjukkan nilai port number di node tujuan.

   Sequence Number: 32 bits
   Mengidentifikasi posisi segmen data.

   Acknowledgment Number: 32 bits
   Mengkonfirmasi apakah data berhasil diterima oleh receiver atau tidak dengan memberikan pesan kembalian ke sender.

   Data Offset: 4 bits
   Mengindikasi nilai dimana data mulai.

   Reserved: 6 bits
   Untuk digunakan di waktu yang akan datang, nilainya harus 0.

   Control Bits: 6 bits (dari kiri ke kanan):
   URG:  Urgent Pointer field significant, berisi informasi untuk receiver
   ACK:  Acknowledgment field significant, berisi informasi untuk receiver
   PSH:  Fungsi push
   RST:  Reset koneksi
   SYN:  Sinkronisasi sequence number
   FIN:  Menutup koneksi

   Window: 16 bits
   Menangani flow control. Mengindikasikan berapa bytes yang bisa dikirim oleh sender ke receiver.

   Checksum: 16 bits
   Mengecek apakah data yang dikirim corrupt atau tidak ketika melakukan transmisi.

   Padding: variable
   Untuk memastikan ukuran TCP header adalah kelipatan 32 bits.
