# Sliding Window
---------------------

TUBES JARKOM 1

**Petunjuk penggunaan program.**

	1. Build menggunakan make
	2. Jalankan 
	3. Jalankan

**Cara kerja program sliding window.**

	1. Data disimpan dalam file txt
	2. Program akan membaca file tersebut sebagai data, dengan ekivalensi 1 char di file txt = 1 byte data
	3. Program kemudian akan mengirim data tersebut sesuai dengan ukuran window dan kemudian dimasukkan ke dalam file buffer
	4. Program receiver akan menerima data dan kembali menuliskan data tersebut ke file txt yang berbeda.

**Pembagian tugas.**

 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| NIM/Nama                      |      Pembagian Tugas          |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| 13515046/Lathifah Nurrahmah   |  receiver file, ack           |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| 13515109/Harum Lokawati       |                               |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| 13515127/Fildah Ananda A      |                               |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

**Pertanyaan:**


	1. Apa yang terjadi jika advertised window yang dikirim bernilai 0? Apa cara untuk menangani hal tersebut? 
	Jawab: 
	Jika advertised window yang dikirim bernilai 0, maka data apapun tidak bisa dikirim. 
	Hal ini disebabkan send buffer penuh sehingga TCP akan melakukan block terhadap proses pengiriman. Ketika data sudah dikeluarkan dari buffer, maka proses pengiriman akan kembali dilakukan. 
	Ketika hal ini terjadi maka sending side akan terus mengirimkan 1 byte data segmen. Meskipun data kemungkinan tidak akan diterima, tetapi usaha ini tetap dilakukan karena setiap 1 byte data segmen yang dikirimkan tersebut akan men-trigger respon yang berisi nilai advertised window yang terbaru.Dengan cara inilah akan didapat respon yang melaporkan bahwa advertised window tidak lagi bernilai 0.

	2. Sebutkan field data yang terdapat TCP Header serta ukurannya, ilustrasikan, dan jelaskan kegunaan dari masing-masing field data tersebut! 
	Jawab:

	0                   1                   2                   3 
	0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
	|          Source Port         |        Destination Port        | 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
	|                        Sequence Number                        | 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
	|                     Acknowledgment Number                     | 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
	|  Data |          |U|A|P|R|S|F|                                | 
	| Offset| Reserved |R|C|S|S|Y|I|             Window             | 
	|       |          |G|K|H|T|N|N|                                | 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
	|           Checksum           |         Urgent Pointer         | 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
	|          Options             |            Padding             | 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
	|                            data                               | 
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

	1. Source Port (16 bits) untuk menunjukkan nilai port number di node asal.

	2. Destination Port (16 bits) untuk menunjukkan nilai port number di node tujuan.

	3. Sequence Number (32 bits) untuk mengidentifikasi posisi segmen data.

	4. Acknowledgment Number (32 bits) untuk mengkonfirmasi apakah data berhasil diterima oleh receiver atau tidak dengan memberikan pesan kembalian ke sender.

	5. Data Offset (4 bits) untuk mengindikasikan nilai dimana data mulai.

	6. Reserved (6 bits) Untuk digunakan di waktu yang akan datang, nilainya harus 0.

	7. Control Bits (6 bits) (dari kiri ke kanan): 
	   URG: Urgent Pointer field significant, berisi informasi untuk receiver 
	   ACK: Acknowledgment field significant, berisi informasi untuk receiver 
	   PSH: Fungsi push 
	   RST: Reset koneksi 
	   SYN: Sinkronisasi sequence number 
	   FIN: Menutup koneksi

	8. Window (16 bits) untuk menangani flow control. Mengindikasikan berapa bytes yang bisa dikirim oleh sender ke receiver.

	9. Checksum (16 bits) untuk mengecek apakah data yang dikirim corrupt atau tidak ketika melakukan transmisi.

	10. Padding merupakan variable Untuk memastikan ukuran TCP header adalah kelipatan 32 bits.
