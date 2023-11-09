package lintuhaaste.data

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.navigation.NavController
import com.google.firebase.firestore.CollectionReference
import com.google.firebase.firestore.FirebaseFirestore
import lintuhaaste.databinding.FragmentAddBinding
import lintuhaaste.databinding.FragmentEditBinding

class ListViewModel : ViewModel() {

    lateinit var navController: NavController

    private val mFirestore = FirebaseFirestore.getInstance()
    private val database = mFirestore.collection("havainnot")

    lateinit var currentSighting: Sighting

    var allSightings: ArrayList<Sighting> = ArrayList()

    val filteredList = ArrayList<Sighting>()

    fun setNav(nav: NavController) {
        navController = nav
    }

    // Create new Sighting object and send it to Firestore
    fun addNew(binding: FragmentAddBinding, date: String) {
        val species = binding.editSpecies.text.toString().lowercase()
        val loc = binding.editLocation.text.toString()
        val notes = binding.editNotes.text.toString()
        val newSighting = Sighting(date, species, loc, notes)
        database.document(species).set(newSighting)
    }

    // Set current sighting
    fun setCurrent(current: Sighting) {
        currentSighting = current
    }

    // Delete item from database, return info of success/failure
    fun deleteSighting(): Boolean {
        var success = true
        val species = currentSighting.getSpecies()
        allSightings.remove(currentSighting)
        database.document(species)
            .delete()
            .addOnSuccessListener { Log.d("MainActivity", "DocumentSnapshot successfully deleted!") }
            .addOnFailureListener { e -> Log.w("MainActivity", "Error deleting document", e)
                success = false}

        return success
    }

    // Update the data of the current sighting locally and in Firestore
    fun updateSighting(binding: FragmentEditBinding, selectedDate: String) {
        currentSighting.setDate(selectedDate)
        currentSighting.setLocation(binding.editLocation.text.toString())
        currentSighting.setNotes(binding.editNotes.text.toString())
        database.document(currentSighting.getSpecies()).set(currentSighting)
    }

    // Query of the current state of Firestore
    fun changeQuery() {
        Log.d("ListViewModel", "muutoskysely kutsuttu")
        database.addSnapshotListener { queryDocumentSnapshots, e ->
                allSightings.clear()
                Log.d("ListViewModel", "nakyman paivitys?")
                if (queryDocumentSnapshots != null) {
                    for (snapshot in queryDocumentSnapshots) {
                        val sight = snapshot.toObject(Sighting::class.java)
                        allSightings.add(sight)
                    }
                    allSightings.sortByDescending {it.reverseDate()  }
                } else {
                    Log.d("ListViewModel", "Querysnapshot on null")
                }
            }
    }
}