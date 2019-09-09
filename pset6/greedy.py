def main():

	while True:
		try:
			cash = float(input("Amount: "))
		except ValueError:
			continue
		else:
			if cash > 0 and cash < 100:
				break
			else:
				continue

	quarter, dime, nickle, penny = 0,0,0,0

	while cash >= 0.25:
		cash -= 0.25
		quarter += 1

	while cash >= 0.10:
		cash -= 0.10
		dime += 1

	while cash >= 0.05:
	    cash -= 0.05
	    nickle += 1

	while cash >= 0.01:
		cash -= 0.01
		penny += 1

	print(quarter)
	print(dime)
	print(nickle)
	print(penny)


if __name__ == "__main__":
	main()
