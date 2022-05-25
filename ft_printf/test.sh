cc main.c ft_printf.c -o ft_pr
./ft_pr > out_ft_pr
cc -D FLAG main.c ft_printf.c -o pr
./pr > out_pr
diff -y --suppress-common-lines out_ft_pr out_pr
rm ft_pr out_ft_pr pr out_pr