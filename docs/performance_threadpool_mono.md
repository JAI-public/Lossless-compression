# Performance (Monochrome Model)
**Environment**: Intel(R) Core(TM) i9-10900X CPU @ 3.70GHz 32Gb, Windows10 Pro 21H2<br>
**Items to Check**:　BUSPLayer should draw images continuously and the program should not crash. In the meantime, modified the program to output logs and measured the processing time.<br>
**Camera**: 20405M PGE<br>
**Image Size**: 4480x4480<br>
**FPS**: Approx. 5.6Hz<br>
**GAIN**: 1
|Image# | thread_num=01 | thread_num=10 | thread_num=20
|--|--|--|--
| 1 |  6.89 | 21.17 | 11.63 
| 2 |  4.87 | 11.58 | 13.60 
| 3 |  5.11 | 15.56 |  9.22 
| 4 |  5.02 | 16.31 | 10.79 
| 5 |  5.19 | 11.93 |  8.97 
| 6 |  6.46 | 11.68 | 15.82 
| 7 |  4.93 | 11.39 | 13.91 
| 8 |  4.95 | 12.03 | 22.94 
| 9 |  4.99 | 15.50 | 15.38 
|10 |  5.03 |  6.88 | 17.94 
|11 |  4.95 |  5.58 | 20.32 
|12 |  5.01 | 16.32 | 12.38 
<br>

![image](https://user-images.githubusercontent.com/107820102/180385211-c931b3e5-abe0-4329-8835-2e046fad94c7.png)
<br>
&emsp; thread_num=01
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; thread_num=10
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; thread_num=20
<br>
&emsp;<img width="220" alt="thread_num_1_4480_4480_5Hz" src="https://user-images.githubusercontent.com/107820102/180964058-41d710d9-dc22-4be7-860a-5ce05785a761.png">
&emsp;<img width="220" alt="thread_num_10_4480_4480_5Hz" src="https://user-images.githubusercontent.com/107820102/180963914-899837e4-4e16-4b7f-96ce-e322312c6387.png">
&emsp;<img width="220" alt="thread_num_20_4480_4480_5Hz" src="https://user-images.githubusercontent.com/107820102/180963562-3fc73f5b-69fa-4eb9-9d69-82a082b59741.png">
