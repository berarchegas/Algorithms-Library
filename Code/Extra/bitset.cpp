// bitset
//
// deve ser inicializado com um valor constante
const int N = 50;
bitset<N> bit;
// pode receber uma string binaria ou um int
bit = "1010", bit = 13;
bit.count() // quantas posicoes acesas
bit.set() // acende tudo
bit.set(3) // acende a posicao 3
bit.reset() // apaga tudo
bit.reset(4) // apaga a posicao 4
bit.flip() // flipa tudo
bit.flip(2) // flipa a posicao 2
string a = bit.to_string() // transforma em string
bit &= bit
bit |= bit
bit ^= bit 