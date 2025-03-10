# Tugas 02: Implementasi Stack dalam Validasi Ekspresi, Konversi Infix ke Postfix, dan Evaluasi Postfix
Nama      : Tasya Zahrani
NPM       : 2308107010006
Kelas     : Struktur Data dan Algoritma D

## Deskripsi Tugas
Tugas ini bertujuan untuk mengimplementasikan konsep struktur data Stack dalam tiga kasus utama:
- Validasi ekspresi tanda kurung menggunakan stack berbasis array.
- Konversi ekspresi aritmatika infix ke postfix menggunakan stack berbasis linked list.
- Evaluasi hasil dari ekspresi postfix menggunakan stack berbasis array dan linked list.

## Struktur Folder
```
Tugas02/
│── infix.c                   
│── infix.exe                 
│── perhitunganPostfix.c      
│── perhitunganPostfix.exe   
│── periksaTandaKurung.c      
│── periksaTandaKurung.exe    
│── README.md                
│── Tugas02.c                 # File utama yang menggabungkan semua fungsi
│── Tugas02.exe               # File eksekusi utama program
```

1. Validasi Ekspresi Tanda Kurung Seimbang
Deskripsi
Program menerima input berupa ekspresi tanda kurung dan memeriksa apakah ekspresi tersebut seimbang atau tidak seimbang.
Contoh Ekspresi:
- ✅ (({({([[( ) ( )]])})})) → Seimbang
- ❌ ([{({([[( ) ( )]))})})) → Tidak seimbang

2. Konversi Ekspresi Infix ke Postfix
Deskripsi
Program mengubah ekspresi aritmatika infix (dengan tanda kurung seimbang) menjadi postfix.
Contoh:
- Input (Infix): (3+5) * 2
- Output (Postfix): 35 + 2*

3. Evaluasi Ekspresi Postfix
Deskripsi
Program menghitung hasil dari ekspresi aritmatika postfix yang telah dikonversi dari infix.
Contoh:
- Input (Postfix): 35 + 2*
- Output: 16

## Catatan
- Pastikan ekspresi tanda kurung memiliki pasangan yang seimbang.
- Gunakan operator valid dalam ekspresi infix (misalnya +, -, *, /, ^).
- Pastikan ekspresi postfix hanya mengandung angka dan operator yang sesuai.

Dapat juga dilihat di github melalui link berikut ini https://github.com/tasyazahrani/2306_TasyaZahrani_SDATugas02.git  

(c) 2025 - tasyazahrani