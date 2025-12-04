use std::io;
use std::io::Write;
use std::cmp::Ordering;

use rand::Rng;

fn main() {
    println!("Guess the number!");
    let secret = rand::thread_rng().gen_range(1..=100);
    println!("Secret: {secret}");

    loop {

        // println!("Input your guess.");
        print!("guess> ");
        let _ret = io::stdout().flush();

        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        match guess.cmp(&secret) {
            Ordering::Less => println!("Greater than {guess}"),
            Ordering::Greater => println!("Less than {guess}"),
            Ordering::Equal => {
                println!("Correct");
                break;
            }
        }
    }
}
