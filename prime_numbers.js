// compute primes up to max number using the Sieve algorithm
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes


function print_usage(name) {
    console.log(`node ${name} <max_number>`);
}

function* range(start, stop, step = 1) {
    if (typeof stop === 'undefined') {
        // one param defined
        stop = start;
        start = 0;
    }

    for (let i = start; step > 0 ? i < stop : i > stop; i += step) {
        yield i;
    }
}

function create_number_list(max) {
    var numbers = new Uint32Array(parseInt(max/2));
    var counter = 0;
    for (let i of range(1, max, 2)) {
        numbers[counter] = i;
        counter += 1;
    }
    return numbers;
}

function mark_multiples_of_prime(numbers, prime_index, max) {
    // print('Checking prime:{}'.format(prime))

    prime = numbers[prime_index];
    array_length = numbers.length;

    // the for loop will start at one multiple past the current prime
    // it will walk the list of numbers by multiples of prime
    // this logic removes the need for any if statements inside the loop
    for (let i of range(prime_index+prime, array_length, prime)) {
        numbers[i] = 0;
    }
}

function compute_primes(max) {
    var start_time = Date.now();
    var numbers = create_number_list(max);

    console.log(`Computing primes from 0 to ${max}`);

    half_length = parseInt(numbers.length / 2);

    for (let index of range(1, half_length)) {
        if (numbers[index] > 1) {
            mark_multiples_of_prime(numbers, index, max);
        }
    }

    var primes = [];
    for (let i of numbers) {
        if (i > 0) {
            primes.push(i);
        }
    }

    var finish_time = Date.now();
    //console.log(primes);

    console.log(`Start: ${parseInt(start_time/1000)}, Finish: ${parseInt(finish_time/1000)}`);
    var time = (parseInt((finish_time - start_time) / 1000));
    console.log(`Compute time: ${time} seconds.`);
    console.log(`Found ${primes.length} prime numbers less than ${max}`);
}

function main() {
    if (process.argv.length > 2) {
        compute_primes(parseInt(process.argv[2]));
    } else {
        print_usage(process.argv[1]);
    }
}


if (require.main === module) {
    main();
}
