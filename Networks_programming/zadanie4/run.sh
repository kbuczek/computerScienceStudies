xterm -e ./serwer_udp_sumaliczb
ncat --udp 127.0.0.1 2020 < test01-dane.txt > wynik-z-serwera1.txt
xterm -e ./serwer_udp_sumaliczb
ncat --udp 127.0.0.1 2020 < test02-dane.txt > wynik-z-serwera2.txt
xterm -e ./serwer_udp_sumaliczb
ncat --udp 127.0.0.1 2020 < test03-dane.txt > wynik-z-serwera3.txt