fn main() {

    let x = 5;
    let x = x + 1;
    {
        let x = x * 2;
        println!("inner scope x: {x}");
    }

    // SHADOWING
    let spaces = "    ";        // spaces is first a string
    let spaces = spaces.len();  // spaces.len() returns a number, thus making spaces a number

    println!("spaces: {spaces}");

}
