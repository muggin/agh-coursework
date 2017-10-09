from datetime import datetime
from django.contrib.auth.models import User
from django.db import models

# Create your models here.
from django.utils import timezone
from modules.accommodations.models import Listing


class Reservation(models.Model):
    owner = models.ForeignKey(User)
    reservation_start = models.DateField(default=timezone.now())
    reservation_end = models.DateField(default=timezone.now() + timezone.timedelta(days=1))
    listing = models.ForeignKey(Listing)
