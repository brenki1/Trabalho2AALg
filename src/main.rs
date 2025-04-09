use std::time::Instant;

fn main() {
    let t = 70;
    let coins = vec![1, 5, 10, 25, 50, 100];
    let mut moedas_usadas = vec![0; (t + 1) as usize];
    let mut cont_moedas = vec![0; (t + 1) as usize];

    println!("Do algoritmo naive que utiliza recursão: ");
    let inicio1 = Instant::now();
    let resultado = alg_troco_rec(&coins, t);
    let fim1 = Instant::now();
    println!("O número de moedas para o troco de {} foi: {}, e o tempo de execução foi de {:?}", t, resultado, fim1-inicio1);

    println!("");

    println!("Do algoritmo que implementa Programação Dinâmica: ");
    print!("Para o troco de {} foram necessárias", t);

    let inicio = Instant::now();
    println!(" {} moedas", alg_troco_pd(&coins, t, &mut cont_moedas, &mut moedas_usadas));
    let fim = Instant::now();
    

    println!("São elas:");
    print_moedas(&moedas_usadas, t);
    println!("Lista de moedas mínimas:");
    println!("{:?}", &moedas_usadas);
    println!("O algoritmo demorou {:?} para encontrar a solução ótima ", fim-inicio);

}

fn alg_troco_rec(moedas: &[i32], t: i32) -> i32 {
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

fn alg_troco_pd(moedas: &[i32], troco: i32, min_moedas: &mut Vec<i32>, moedas_usadas: &mut Vec<i32>) -> i32 {
    for centavos in 0..=troco {
        let mut cont_moeda = centavos;
        let mut nova_moeda = 1;
        
        for &moeda in moedas.iter().filter(|&&c| c <= centavos) {
            if min_moedas[(centavos - moeda) as usize] + 1 < cont_moeda {
                cont_moeda = min_moedas[(centavos - moeda) as usize] + 1;
                nova_moeda = moeda;
            }
        }
        
        min_moedas[centavos as usize] = cont_moeda;
        moedas_usadas[centavos as usize] = nova_moeda;
    }
    
    min_moedas[troco as usize]
}

fn print_moedas(moedas_usadas: &[i32], troco: i32) {
    let mut coin = troco;
    
    while coin > 0 {
        let this_coin = moedas_usadas[coin as usize];
        println!("{}", this_coin);
        coin -= this_coin;
    }
}