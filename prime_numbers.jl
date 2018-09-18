# compute primes up to max using the Sieve algorithm
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# https://docs.julialang.org/en/v1/


import Dates

function print_usage()
  println(string("julia ", PROGRAM_FILE, " max_prime"))  
end

function make_array(max)
  return collect(1:2:max)
end

function remove_multiples(numbers, prime_index, max)

  prime::Int64 = numbers[prime_index]
  array_length::Int64 = length(numbers)

  # println("called remove_multiple(", prime_index, ") = ", prime, ", length: ", array_length)

  # the for loop will start at one multiple pass the current prime
  # it will walk the list of numbers by multiples of prime
  # this logic removes the need for any if statements inside the loop
  @inbounds for current_index::Int64 in prime_index+prime : prime : array_length
    numbers[current_index] = 0
  end
end

function compute_primes(max::Int64)
  start_time = Dates.now()

  numbers = make_array(max)

  # println(numbers)
  # println("Length: ", length(numbers))

  println("Computing primes from 0 to ", max)

  @inbounds for i = 2:(Int64(length(numbers)/2))
    if numbers[i] > 0
      remove_multiples(numbers, i, max)
    end
  end


  primes = filter(x -> x>0, numbers)

  mid_time = Dates.now()

  # println("Primes: ", primes)

  finish_time = Dates.now()

  println("Start: ", start_time, ", Mid: ", mid_time, ", Finish: ", finish_time)
  println("Compute time: ", (mid_time - start_time))
  println("Found: ",  length(primes), " prime numbers under: ", max)
end

function main()
  if length(ARGS) < 1
    print_usage()
  else
    compute_primes(parse(Int64, ARGS[1]))
  end

end

main()
