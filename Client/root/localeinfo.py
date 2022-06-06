#en alta ekle

def PrivateShopSecondToDHMS(time):
	if time < 60:
		return "%.2fseg." % time

	second = int(time % 60)
	minute = int((time / 60) % 60)
	hour = int((time / 60) / 60) % 24
	day = int(int((time / 60) / 60) / 24)

	text = ""

	if day > 0:
		text += str(day) + "d "
		text += " "

	if hour > 0:
		text += str(hour) + "h "
		text += " "

	if minute > 0:
		text += str(minute) + "m "

	if second > 0:
		text += str(second) + "s "

	return text

def NumberToDecimalString(n):
	return str('.'.join([ i-3<0 and str(n)[:i] or str(n)[i-3:i] for i in range(len(str(n))%3, len(str(n))+1, 3) if i ]))

def NumberToMoneyStringWithIcon(n):
	if n <= 0:
		return "0 %s" % "|Eoutras_imagens/money|e"

	return "%s %s" % ('.'.join([ i-3<0 and str(n)[:i] or str(n)[i-3:i] for i in range(len(str(n))%3, len(str(n))+1, 3) if i ]), "|Eoutras_imagens/money|e")