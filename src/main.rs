use std::time::Instant;

fn main() {
    let coins: [i32; 6] = [1, 5, 10,25,50,100];

    let troco = 80;

    let inicio = Instant::now();
    let resultado = alg_troco_rec(coins, 80);
    let fim: Instant = Instant::now();

    println!("O numero de moedas para o troco de {} foi: {}, e o tempo de execução foi de {:?}", (troco/100), resultado, (fim-inicio));
}

fn alg_troco_rec(moedas: [i32;6], t: i32) -> i32 {
    let mut min_moedas: i32 = t;

    if moedas.contains(&t) {
        return 1;
    }

    for &coin in moedas.iter().filter(|&&c| c <= t) {
        let num_moedas = 1 + alg_troco_rec(moedas, t - coin);
        if num_moedas < min_moedas {
            min_moedas = num_moedas;
        }
    }

    return min_moedas;
}
