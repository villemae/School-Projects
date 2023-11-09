package lintuhaaste.data

import android.util.Log
import java.util.*

class Sighting(
    private var date: String = "",
    private var species: String = "",
    private var location: String = "",
    private var notes: String = "") {

    fun getDate(): String {
        return date
    }

    fun getSpecies(): String {
        return species
    }

    fun getLocation(): String {
        return location
    }

    fun getNotes(): String {
        return notes
    }

    fun setDate(newDate: String) {
        date = newDate
    }

    fun setSpecies(newSpecies: String) {
        species = newSpecies
    }

    fun setLocation(newLocation: String) {
        location = newLocation
    }

    fun setNotes(newNotes: String) {
        notes = newNotes
    }

    override fun toString(): String {
        return "$date : $species"
    }

    // Inversed date is needed to order the items on the list accordingly (latest sighting first)
    // E.g. 2022.04.12 > 2022.02.24 (true), but 12.04.2022 < 24.02.2022 (false)
    fun reverseDate(): String {
        val dd_MM_yyyy = date.split(".")
        var day = dd_MM_yyyy[0]
        if (day.length < 2) {
            day = "0${dd_MM_yyyy[0]}"
        }
        val reversed_date = "${dd_MM_yyyy[2]}.${dd_MM_yyyy[1]}.$day"
        return reversed_date
    }

}