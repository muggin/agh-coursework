from django.shortcuts import render

# Create your views here.
from django.views import generic
from modules.reservations.models import Reservation


class ReservationCreateView(generic.CreateView):
    template_name = "reservations/reservation_form.html"
    model = Reservation
    fields = '__all__'

    def form_valid(self, form):
        ''' SEND EMAIL TO AUTHOR '''
        super(ReservationCreateView, self).form_valid(form)


class ReservationList(generic.ListView):
    template_name = 'reservations/reservation_list.html'
    context_object_name = 'reservation_list'

    def get_queryset(self):
        listing_dictionary =Reservation.objects.all()
        return listing_dictionary