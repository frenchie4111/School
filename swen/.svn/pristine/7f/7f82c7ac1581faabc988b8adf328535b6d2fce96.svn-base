from django.db import models
from django.contrib.auth.models import User
from ToolShare.apps.ShareZoneManager.models import ShareZone

class UserProfile( models.Model ):
	user = models.ForeignKey(User, unique=True)
	ShareZone = models.ForeignKey( ShareZone, db_column='zipcode' )

	def __str__(self):
		return "%s's profile" % self.user
