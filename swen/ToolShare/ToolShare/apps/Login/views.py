from django.http import HttpResponse
from django.shortcuts import render
from django.contrib.auth.models import User

def login(request):
	return render( request, "main.html", {"child":"Login/login.html"} )
