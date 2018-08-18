# Eratosthenes-Sieve
A simple sieve of Eratosthenes implementation to generate a list of primes that are no larger than a specified upper limit.

The sieve will be stored as a vector of booleans. To save memory (and probably a little bit execution time) we'll only store odd numbers

## Usage (with `<limit>` not less than 2):

Run the command as

```
./prime <limit> [breakat]
```

to print all primes up to `<limit>` with a line break after every `[breakat]` elements

By default `breakat = 10`. To print without any line breaks set `breakat = 0`
