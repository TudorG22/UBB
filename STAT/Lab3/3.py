from scipy.stats import binom
from matplotlib.pyplot import hist, bar, legend, grid, show


X = binom(5, 0.6)
data = X.rvs(size=1000) # a)

bin_edges = [i - 0.5 for i in range(7)] # b)
hist(data, bin_edges, density=True, rwidth=0.9, color='green',
     alpha=0.5, label='frecvente relative')
bar(range(6), [X.pmf(i) for i in range(6)], width=0.85,
    color='red', alpha=0.6, label='probabilitati teoretice')

prob_estimata = sum(1 < x <= 4 for x in data) / 1000 # c)
prob_teoretica = X.cdf(4) - X.cdf(1)
print('Probabilitate estimata:', prob_estimata)
print('Probabilitate teoretica:', prob_teoretica)

legend()
grid()
show()
