from django.http import HttpResponse
from django.shortcuts import render
from django.contrib.auth.models import User
from ToolShare.helpers import isNumber
from ToolShare.apps.ProfileManager.models import UserProfile
from ToolShare.apps.ShareZoneManager.models import ShareZone

def respondToRegistration( flash, flash_negative ):
	return render( request, "main.html", { "child" : "Registration/index.html", "flash" : flash, "flash_negative" : flash_negative } )
	
def index(request):
	if( request.method == "GET" ):
		# Render main html and tell it the child is Registraion/index
		return render( request, "main.html", { "child" : "Registration/index.html" } )
	elif( request.method == "POST" ):
		try:
			first_name = request.POST["first_name"]
			last_name = request.POST["last_name"]
			
			username = request.POST["username"]
			# Need to validate email( username ) using standard email regex
			password = request.POST["password"]
			password2 = request.POST["password2"]

			# Check if passwords match
			if( password != password2 ):
				return respondToRegistration( "Passwords do not match", True )

			zipcode = request.POST["zipcode"]
			# Check if zipcode is a number
			if( not isNumber( zipcode ) ):
				return respondToRegistration( "Zipcode is not a number", True )
			if( not len( zipcode ) ):
				return respondToRegistration( "Zipcode is an incorrect length", True )
				
			if( first_name == "First Name" ):
				return respondToRegistration( "First name is not filled out", True )
			if( last_name == "Last Name" ):
				return respondToRegistration( "Last name is not filled out", True )
			if( email == "Email" ):
				return respondToRegistration( "Email field is not filled out", True )
			if( password == "password" or password2 == "password" ):
				return respondToRegistration( "Password field is not filled out", True )
				
		except (KeyError):
			return respondToRegistration( "Something went terribly wrong", True )
		else:
			sharezone = ShareZone.objects.get_or_create( zipcode=zipcode )
			user = User.objects.create_user( username, username, password, first_name=first_name, last_name=last_name )
			UserProfile.objects.create( ShareZone=sharezone[0], user=user )
		return respondToRegistration( "Account creation successful", False )
