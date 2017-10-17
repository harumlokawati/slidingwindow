# slidingwindow
-----------------
TUBES JARKOM 1

**Petunjuk penggunaan program.**
**Cara kerja program sliding window.**
**Pembagian tugas.**


**Pertanyaan:**
1.	Apa yang terjadi jika advertised window yang dikirim bernilai 0? Apa cara untuk menangani hal tersebut?
Jawab: 
Jika advertised window yang dikirim bernilai 0, maka data tidak bisa dikirim. Receiver akan menunggu sender untuk kembali mengirimkan data tersebut.


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
