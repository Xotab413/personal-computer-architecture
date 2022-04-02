# Links for undestanding material
- First u should read [lecture](https://docviewer.yandex.by/view/853638837/?page=1&*=C8T7IsGL3IfOr0HuMnf1gqvsAs17InVybCI6InlhLWRpc2stcHVibGljOi8vaGNYTnJMVzk1V3BiVlMybVdEekVRN1dzQkZnbk1OY3YzeVdVdFgwQVJrUEoyL1JmTkpyT3JraWlYamx0aUZkWStiM25DS0xDVlRKK1NJbmFPVXZ2SFE9PTov0JvQtdC60YbQuNC4Lz0zPdCn0KDQki5wcHQiLCJ0aXRsZSI6Ij0zPdCn0KDQki5wcHQiLCJub2lmcmFtZSI6ZmFsc2UsInVpZCI6Ijg1MzYzODgzNyIsInRzIjoxNjQ4NDUxMDQwNDE5LCJ5dSI6Ijc2NTIyMDIyMzE2MzgxMDg1MzIifQ%3D%3D) 
- and understand how CMOS works,
    <br> if u don't understand read [this](https://www.frolov-lib.ru/books/bsp/v02/ch4.htm) link
    </br>
-  When u copy_paste, or write code by your own,
  <br> u should understand all comand which u use, what bytes and why, read clearly [book](https://drive.google.com/file/d/1aG7Vo_kJ4ZMPGaH0aOFx7MC1hDn_T09z/view?usp=sharing) p 316</br>
## NOTE

+ This is cool lab, because ~~Odinec hate 0x4A interruption~~, and if u have it that's bad (this is all labs in git and helper)
> UPD: you have 2 chairs, but firslty read this [article][why70h] : 1 - redefine interruption handlers for [int70h], for alaram and for delay (yeah, you'll have 2 "similar"), 2 - nd chair is my theory, and mb in future it will fail, but who knows). We can redefine int of alarm 4ah (vector), and for delay 15h, and MAybe it's should work. The reason why on Anjelika's github and other's it's do not work, because if we redefine 70h which include also (4ah and 15h with services), we should properly redefine the same vector for alarm, and if you try to set alarm and use delay, you'll have a lot of message "alarm", and seg error :3
+ Just relax and do your best (◕_◕)
+ Use virtualbox because DOSbox doesn't have BIOS


[int70h]:http://vitaly_filatov.tripod.com/ng/asm/asm_001.16.html 
[why70h]: https://www.compuphase.com/int70.txt
