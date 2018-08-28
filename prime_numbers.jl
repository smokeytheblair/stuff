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

  @inbounds for i in prime_index : prime : array_length
    current_index::Int64 = Int64(i)

    if current_index <= array_length && numbers[current_index] > prime
      # println("i = ", i, " - Removing numbers[",current_index , "] = ", numbers[current_index])
      numbers[current_index] = 0
    end
  end
end

function main()
  if length(ARGS) < 1
    print_usage()
  else
    max = parse(Int64, ARGS[1])

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
    println("Compute time: ", mid_time - start_time)
    println("Found: ",  length(primes), " prime numbers under: ", max)

  end

end

main()
