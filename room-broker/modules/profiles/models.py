from django.db import models
from django.contrib.auth.models import User

# Create your models here.


class Profile(models.Model):
    user = models.OneToOneField(User)
    id_number = models.CharField(max_length=9, blank=True)
    phone_number = models.IntegerField(blank=True)
    activated = models.BooleanField(default=False)