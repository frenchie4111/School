from django.db import models

class ShareZone( models.Model ):
	zipcode = models.IntegerField( unique=True )
	
	def __str__(self):
		return "%d" % self.zipcode
