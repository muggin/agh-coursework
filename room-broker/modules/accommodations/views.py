from modules.accommodations.models import Listing, Accommodation
from modules.accommodations.forms import ListingForm
from django.views import generic
from django.core.urlresolvers import reverse_lazy

# Create your views here.


class ListingListView(generic.ListView):
    template_name = 'accommodations/listing/listing_list.html'
    context_object_name = 'listing_extended_list'

    def get_queryset(self):
        listing_extended_list = [
            ('active listings', True, Listing.objects.filter(expired=False)),
            ('expired listings', False, Listing.objects.filter(expired=True))
        ]
        return listing_extended_list


class ListingDetailView(generic.DetailView):
    template_name = 'accommodations/listing/listing_detail.html'
    model = Listing

    def get_object(self, queryset=None):
        object = super(ListingDetailView, self).get_object()
        if not object.expired:
            object.view_count += 1
        object.save()
        return object


class ListingCreateView(generic.CreateView):
    template_name = 'accommodations/listing/listing_form.html'
    model = Listing
    fields = '__all__'
    success_url = reverse_lazy('accommodations:listing_list')

    def form_valid(self, form):
        ''' SEND EMAIL TO AUTHOR '''
        super(ListingCreateView, self).form_valid(form)


class ListingUpdateView(generic.UpdateView):
    template_name = 'accommodations/listing/listing_form.html'
    model = Listing
    fields = ['view_count']
    success_url = reverse_lazy('accommodations:listing_list')


class ListingDeleteView(generic.DeleteView):
    template_name = 'accommodations/listing/listing_confirm_delete.html'
    model = Listing
    success_url = reverse_lazy('accommodations:listing_list')


class AccommodationListView(generic.ListView):
    template_name = 'accommodations/listing/listing_list.html'
    context_object_name = 'accommodation_list'
    model = Accommodation

    def get_queryset(self):
        listing_extended_list = [
            ('accommodation list', True, Listing.objects.filter(expired=False)),
            ('expired listings', False, Listing.objects.filter(expired=True))
        ]
        return listing_extended_list


class AccommodationDetailView(generic.DetailView):
    template_name = 'accommodations/listing/listing_detail.html'
    model = Accommodation




