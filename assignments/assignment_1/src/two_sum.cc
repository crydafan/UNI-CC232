#include <unordered_map>

#include "two_sum.hh"

// https://leetcode.com/problems/two-sum/submissions/1965012909
/*
Usando un hash map para guardar los indices de los numeros que ya hemos visto, iteramos por el arreglo
y por cada numero calculamos el resto (target - nums[i]) y buscamos en el hash map si ese 
resto ya lo hemos visto antes. Si lo encontramos, entonces tenemos la solucion y retornamos los indices.
Si no lo encontramos, guardamos el numero actual en el hash map con su indice.
*/
std::vector<int> two_sum(const std::vector<int> &nums, int target) {
  std::unordered_map<int, int> indices;

  for (int i = 0; i < nums.size(); ++i) {
    int remainder = target - nums[i];

    if (indices.find(remainder) != indices.end())
      return {indices[remainder], i};

    indices[nums[i]] = i;
  }

  return {};
}

/*
Por fuerza bruta con bucle anidado.
Usa dos bucles anidados. El primer bucle (i) agarra un numero y el segundo bucle (j) lo compara con
todos los demas numeros del arreglo para ver si suman el target.
*/
std::vector<int> two_sum_naive(const std::vector<int> &nums, int target) {
  for (int i = 0; i < nums.size(); ++i) {
    for (int j = i + 1; j < nums.size(); ++j) {
      if (nums[i] + nums[j] == target)
        return {i, j};
    }
  }

  return {};
}
