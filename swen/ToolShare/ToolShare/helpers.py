def isNumber( str ):
	try:
		float( str )
		return True
	except ValueError:
		return False