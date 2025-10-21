use std::fs;

fn main() {
    let input = fs::read_to_string("../inputs/06.txt").unwrap();
    // let input = fs::read_to_string("./example.txt").unwrap();
    let dist_over_time: Vec<_> = input
        .lines()
        .map(|l| {
            Vec::from_iter(
                l.split_whitespace()
                    .skip(1)
                    .filter_map(|num| num.parse::<u64>().ok()),
            )
        })
        .rev()
        .collect();

    let dist_over_time = transpose(dist_over_time);

    let p1 = dist_over_time
        .iter()
        .map(|dt| match &dt[..] {
            [dist, time] => ways_to_win(*dist, *time),
            _ => panic!("malformed imput."),
        })
        .fold(1, |a, b| a * b);

    println!("Part 1: {p1}");

    let mut dist = 0;
    let mut time = 0;
    for (i, line) in input.lines().enumerate() {
        let num = line
            .split_whitespace()
            .skip(1)
            .collect::<Vec<_>>()
            .join("")
            .parse::<u64>()
            .unwrap();

        match i {
            0 => time = num,
            1 => dist = num,
            _ => unreachable!(),
        }
    }

    let p2 = ways_to_win(dist, time);

    println!("Part 2: {p2}");
}

fn ways_to_win(distance: u64, time: u64) -> u64 {
    // Check the results of accelerating 1 to (time - 1) seconds
    (1..time)
        // Count the scenarious where it beats the record
        .filter(|&i| distance_traveled(i, time) > distance)
        .count() as u64
}

fn distance_traveled(accelerate: u64, time_limit: u64) -> u64 {
    (time_limit - accelerate) * accelerate
}

fn transpose<T: Clone>(matrix: Vec<Vec<T>>) -> Vec<Vec<T>> {
    if matrix.is_empty() || matrix[0].is_empty() {
        return Vec::new();
    }

    let cols = matrix[0].len();

    (0..cols)
        .map(|i| matrix.iter().map(|row| row[i].clone()).collect())
        .collect()
}
